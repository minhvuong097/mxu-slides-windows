qt_add_executable(tst_mxu_document tst_document.cpp)
target_link_libraries(tst_mxu_document PRIVATE
    mxu_core mxu_shell
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Test
)
add_test(NAME tst_mxu_document COMMAND tst_mxu_document)
