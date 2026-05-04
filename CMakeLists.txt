cmake_minimum_required(VERSION 3.13)

project(IAEditorMod)

add_subdirectory(geode)

add_geode_mod(
    ID "adradrigc1214gd.ia_editor" 
    SOURCES src/main.cpp
)
