cmake_minimum_required(VERSION 3.28)
project(1labcpp)

# Опция для выбора директории
set(LAB_NUMBER "4" CACHE STRING "Номер лабораторной работы")

# Список доступных лабораторных работ
set(LAB_DIRECTORIES 1 2 3 4)

# Проверка, что выбранная лабораторная работа существует
if(NOT LAB_NUMBER IN_LIST LAB_DIRECTORIES)
    message(FATAL_ERROR "Неверный номер лабораторной работы.")
endif()

# Подключение соответствующего подпроекта
add_subdirectory(${LAB_NUMBER})