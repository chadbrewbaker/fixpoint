set_source_files_properties(
    "${CMAKE_BINARY_DIR}/_deps/wabt-build/CMakeFiles/wasm2c.dir/src/c-writer.cc.o" PROPERTIES
    EXTERNAL_OBJECT TRUE
    GENERATED TRUE
)

add_executable(compiler_tester "compiler_tester.cc" "${CMAKE_BINARY_DIR}/_deps/wabt-build/CMakeFiles/wasm2c.dir/src/c-writer.cc.o")
target_link_libraries("compiler_tester" runtime compiler runtime compiler)
target_link_libraries("compiler_tester" component)
target_link_libraries("compiler_tester" util)
target_link_libraries("compiler_tester" cryptopp)
target_link_libraries("compiler_tester" wasmrt)
target_link_libraries("compiler_tester" ${CLANG_LIBS})
target_link_libraries("compiler_tester" LLVM)
target_link_libraries("compiler_tester" absl::flat_hash_map )
target_link_libraries("compiler_tester" wabt)
add_dependencies("compiler_tester" wasm2c)

add_executable(compiler_timing "compiler_timing.cc" "${CMAKE_BINARY_DIR}/_deps/wabt-build/CMakeFiles/wasm2c.dir/src/c-writer.cc.o")
target_link_libraries("compiler_timing" runtime compiler runtime compiler)
target_link_libraries("compiler_timing" component)
target_link_libraries("compiler_timing" util)
target_link_libraries("compiler_timing" cryptopp)
target_link_libraries("compiler_timing" wasmrt)
target_link_libraries("compiler_timing" ${CLANG_LIBS})
target_link_libraries("compiler_timing" LLVM)
target_link_libraries("compiler_timing" absl::flat_hash_map )
target_link_libraries("compiler_timing" wabt)
add_dependencies("compiler_timing" wasm2c)

add_executable(c_to_elf_tester "c_to_elf_tester.cc")
target_link_libraries("c_to_elf_tester" util)
target_link_libraries("c_to_elf_tester" compiler)
target_link_libraries("c_to_elf_tester" ${CLANG_LIBS})
target_link_libraries("c_to_elf_tester" LLVM)

add_executable(wasm_to_elf_tester "wasm_to_elf_tester.cc" "${CMAKE_BINARY_DIR}/_deps/wabt-build/CMakeFiles/wasm2c.dir/src/c-writer.cc.o")
target_link_libraries("wasm_to_elf_tester" util)
target_link_libraries("wasm_to_elf_tester" compiler)
target_link_libraries("wasm_to_elf_tester" ${CLANG_LIBS})
target_link_libraries("wasm_to_elf_tester" LLVM)
target_link_libraries("wasm_to_elf_tester" wabt)
add_dependencies("wasm_to_elf_tester" wasm2c)

add_executable(elf_linking_tester "elf_linking_tester.cc")
target_link_libraries("elf_linking_tester" compiler)
target_link_libraries("elf_linking_tester" runtime)
target_link_libraries("elf_linking_tester" component)
target_link_libraries("elf_linking_tester" util)
target_link_libraries("elf_linking_tester" cryptopp)
target_link_libraries("elf_linking_tester" wasmrt)
target_link_libraries("elf_linking_tester" absl::flat_hash_map )

add_executable(elf_to_encode_tester "execute_encode_from_elf.cc")
target_link_libraries("elf_to_encode_tester" runtime compiler runtime compiler)
#target_link_libraries("elf_to_encode_tester" compiler)
target_link_libraries("elf_to_encode_tester" component)
target_link_libraries("elf_to_encode_tester" util)
target_link_libraries("elf_to_encode_tester" cryptopp)
target_link_libraries("elf_to_encode_tester" wasmrt)
target_link_libraries("elf_to_encode_tester" absl::flat_hash_map )

