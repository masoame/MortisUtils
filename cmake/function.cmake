
function(mo_collect_sources_and_includes base_dir out_sources_var out_includes_var)
    set(_src_patterns
        ${base_dir}/*.cpp
        ${base_dir}/*/*.cpp
        ${base_dir}/*/*/*.cpp
    )

    set(_sources)
    foreach(_pat IN LISTS _src_patterns)
        file(GLOB CONFIGURE_DEPENDS _found ${_pat})
        list(APPEND _sources ${_found})
    endforeach()
    list(REMOVE_DUPLICATES _sources)

    # 递归收集头文件所在目录并去重
    file(GLOB_RECURSE CONFIGURE_DEPENDS _headers
        ${base_dir}/*.h
        ${base_dir}/*/*.h
        ${base_dir}/*/*/*.h
        ${base_dir}/*.hpp
        ${base_dir}/*/*.hpp
        ${base_dir}/*/*/*.hpp
    )
    set(_inc_dirs)
    foreach(_h IN LISTS _headers)
        get_filename_component(_d ${_h} DIRECTORY)
        list(APPEND _inc_dirs ${_d})
    endforeach()
    list(REMOVE_DUPLICATES _inc_dirs)

    # 将结果返回给调用者（通过 PARENT_SCOPE）
    set(${out_sources_var} ${_sources} PARENT_SCOPE)
    set(${out_includes_var} ${_inc_dirs} PARENT_SCOPE)
endfunction()
