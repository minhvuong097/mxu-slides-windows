#!/usr/bin/env python3
"""Generate C++20 domain models from the MxU Slides document schema.

Input:  schema/documents.json  (same file used by the macOS codegen.mjs)
Output: src/core/generated/Models.h
        src/core/generated/Models.cpp

Every field added after a type ships must stay optional so older documents
keep decoding — the schema already follows that rule and the generator keeps
std::optional<> for every optional field.
"""

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SCHEMA = ROOT / "schema" / "documents.json"
OUT_DIR = ROOT / "src" / "core" / "generated"
ENUMS: set[str] = set()
RECORDS: set[str] = set()
# Break schema cycles (e.g. Slide -> SlideVersion -> Slide) with shared_ptr.
SHARED_FIELDS = {
    ("AnimationStep", "toObject"): "SlideObject",
    ("AnimationStep", "fromObject"): "SlideObject",
    ("SlideVersion", "slide"): "Slide",
}


def pascal(name: str) -> str:
    return name[0].upper() + name[1:]


def cpp_type(raw: str) -> str:
    if raw == "string":
        return "QString"
    if raw in ("int", "double", "bool"):
        return raw
    if raw.startswith("list:"):
        return f"QVector<{cpp_type(raw[5:])}>"
    return raw  # enum or record name, already PascalCase


def decode_expr(raw: str, value: str, shared: bool = False) -> str:
    if raw == "string":
        return f"{value}.toString()"
    if raw == "int":
        return f"{value}.toInt()"
    if raw == "double":
        return f"{value}.toDouble()"
    if raw == "bool":
        return f"{value}.toBool()"
    if raw.startswith("list:"):
        inner = raw[5:]
        if inner in ENUMS:
            return f"decodeList<{inner}>({value}, {inner}FromString)"
        if inner in RECORDS:
            return f"decodeList<{inner}>({value}, {inner}FromJson)"
        return f"decodeList<{cpp_type(inner)}>({value})"
    if raw in ENUMS:
        return f"{raw}FromString({value}.toString())"
    decoded = f"{raw}FromJson({value}.toObject())"
    return f"std::make_shared<{raw}>({decoded})" if shared else decoded


def encode_expr(raw: str, name: str, shared: bool = False) -> str:
    if raw in ("string", "int", "double", "bool"):
        return name
    if raw.startswith("list:"):
        inner = raw[5:]
        if inner in ENUMS:
            return f"encodeList({name}, [](const {inner}& item) {{ return toString(item); }})"
        if inner in RECORDS:
            return f"encodeList({name}, [](const {inner}& item) {{ return toJson(item); }})"
        return f"encodeList({name})"
    if raw in ENUMS:
        return f"toString({name})"
    inner = f"*{name}" if shared else name
    return f"toJson({inner})"


def main() -> None:
    schema = json.loads(SCHEMA.read_text(encoding="utf-8"))
    types = schema["types"]
    enums = {n: v for n, v in types.items() if v.get("kind") == "enum"}
    records = {n: v for n, v in types.items() if v.get("kind") == "record"}
    ENUMS.update(enums)
    RECORDS.update(records)

    # Emit records only after the records they contain.
    dependencies = {}
    for name, spec in records.items():
        deps = set()
        for field in spec["fields"]:
            raw = field["type"]
            inner = raw[5:] if raw.startswith("list:") else raw
            if inner in records and inner != name:
                deps.add(inner)
        dependencies[name] = deps
    record_order = []
    visiting = set()
    def visit(name):
        if name in record_order or name in visiting:
            return
        visiting.add(name)
        for dep in sorted(dependencies[name]):
            visit(dep)
        visiting.discard(name)
        record_order.append(name)
    for name in records:
        visit(name)

    h = [
        "// Generated from schema/documents.json — do not edit by hand.",
        "// Regenerate: python3 scripts/generate_models.py",
        "#pragma once",
        "",
        "#include <QJsonArray>",
        "#include <QJsonObject>",
        "#include <QString>",
        "#include <QVector>",
        "",
        "#include <memory>",
        "#include <optional>",
        "#include <type_traits>",
        "",
        "namespace mxu::model {",
        "",
    ]

    h.append("// Forward declarations (record dependency graph is acyclic).")
    for name in records:
        h.append(f"struct {name};")
    h.append("")

    for name, spec in enums.items():
        values = ", ".join(pascal(c) for c in spec["cases"])
        h.append(f"enum class {name} {{ {values} }};")
        h.append(f"QString toString({name} value);")
        h.append(f"{name} {name}FromString(const QString& text);")
        h.append("")

    h += [
        "template <typename T>",
        "QJsonArray encodeList(const QVector<T>& values)",
        "{",
        "    QJsonArray array;",
        "    for (const auto& value : values)",
        "        array.append(QJsonValue::fromVariant(QVariant::fromValue(value)));",
        "    return array;",
        "}",
        "",
        "template <typename T, typename Encode>",
        "QJsonArray encodeList(const QVector<T>& values, Encode encode)",
        "{",
        "    QJsonArray array;",
        "    for (const auto& value : values)",
        "        array.append(encode(value));",
        "    return array;",
        "}",
        "",
        "template <typename T>",
        "QVector<T> decodeList(const QJsonValue& value)",
        "{",
        "    QVector<T> result;",
        "    for (const QJsonValue& item : value.toArray()) {",
        f"        if constexpr (std::is_same_v<T, QString>) result.append(item.toString());",
        f"        else if constexpr (std::is_same_v<T, int>) result.append(item.toInt());",
        f"        else if constexpr (std::is_same_v<T, double>) result.append(item.toDouble());",
        f"        else if constexpr (std::is_same_v<T, bool>) result.append(item.toBool());",
        "    }",
        "    return result;",
        "}",
        "",
        "template <typename T, typename Decode>",
        "QVector<T> decodeList(const QJsonValue& value, Decode decode)",
        "{",
        "    QVector<T> result;",
        "    for (const QJsonValue& item : value.toArray())",
        "        result.append(decode(item.toObject()));",
        "    return result;",
        "}",
        "",
    ]

    for name in record_order:
        spec = records[name]
        h.append(f"struct {name}")
        h.append("{")
        for field in spec["fields"]:
            type_name = cpp_type(field["type"])
            if (name, field["name"]) in SHARED_FIELDS:
                type_name = f"std::shared_ptr<{SHARED_FIELDS[(name, field['name'])]}>"
            if field.get("optional"):
                type_name = f"std::optional<{type_name}>"
            h.append(f"    {type_name} {field['name']};")
        h.append("};")
        h.append(f"QJsonObject toJson(const {name}& value);")
        h.append(f"{name} {name}FromJson(const QJsonObject& object);")
        h.append("")

    h.append(f"static constexpr int schemaVersion = {schema['schemaVersion']};")
    h.append("")
    h.append("} // namespace mxu::model")
    h.append("")

    # ---------------- implementation -------------------------------------
    cpp = [
        "// Generated from schema/documents.json — do not edit by hand.",
        '#include "Models.h"',
        "",
        "#include <QJsonArray>",
        "#include <QJsonValue>",
        "",
        "#include <type_traits>",
        "",
        "namespace mxu::model {",
        "",
    ]

    h.append("// Forward declarations (record dependency graph is acyclic).")
    for name in records:
        h.append(f"struct {name};")
    h.append("")

    for name, spec in enums.items():
        cases = spec["cases"]
        cpp.append(f"QString toString({name} value)")
        cpp.append("{")
        cpp.append("    switch (value) {")
        for case in cases:
            cpp.append(f"    case {name}::{pascal(case)}: return QStringLiteral(u\"{case}\");")
        cpp.append("    }")
        cpp.append("    return {};")
        cpp.append("}")
        cpp.append("")
        cpp.append(f"{name} {name}FromString(const QString& text)")
        cpp.append("{")
        for case in cases:
            cpp.append(f"    if (text == QStringLiteral(u\"{case}\")) return {name}::{pascal(case)};")
        for alias, canonical in (spec.get("legacyAliases") or {}).items():
            cpp.append(f"    if (text == QStringLiteral(u\"{alias}\")) return {name}::{pascal(canonical)};")
        cpp.append(f"    return {name}::{pascal(cases[0])};")
        cpp.append("}")
        cpp.append("")

    for name in record_order:
        spec = records[name]
        cpp.append(f"QJsonObject toJson(const {name}& value)")
        cpp.append("{")
        cpp.append("    QJsonObject object;")
        for field in spec["fields"]:
            fname = field["name"]
            raw = field["type"]
            shared = (name, fname) in SHARED_FIELDS
            key = f'QStringLiteral(u"{fname}")'
            if field.get("optional"):
                cpp.append(f"    if (value.{fname})")
                cpp.append(f"        object.insert({key}, {encode_expr(raw, '*value.' + fname, shared)});")
            else:
                cpp.append(f"    object.insert({key}, {encode_expr(raw, 'value.' + fname, shared)});")
        cpp.append("    return object;")
        cpp.append("}")
        cpp.append("")
        cpp.append(f"{name} {name}FromJson(const QJsonObject& object)")
        cpp.append("{")
        cpp.append(f"    {name} value;")
        for field in spec["fields"]:
            fname = field["name"]
            raw = field["type"]
            key = f'QStringLiteral(u"{fname}")'
            expr = decode_expr(raw, f"object.value({key})", (name, fname) in SHARED_FIELDS)
            if field.get("optional"):
                cpp.append(f"    if (object.contains({key}))")
                cpp.append(f"        value.{fname} = {expr};")
            else:
                cpp.append(f"    value.{fname} = {expr};")
        cpp.append("    return value;")
        cpp.append("}")
        cpp.append("")

    cpp.append("} // namespace mxu::model")
    cpp.append("")

    OUT_DIR.mkdir(parents=True, exist_ok=True)
    (OUT_DIR / "Models.h").write_text("\n".join(h), encoding="utf-8")
    (OUT_DIR / "Models.cpp").write_text("\n".join(cpp), encoding="utf-8")
    print(f"generated {len(records)} records and {len(enums)} enums")


if __name__ == "__main__":
    main()
