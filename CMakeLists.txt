cmake_minimum_required(VERSION 3.26)
project(FarmaManage)

set(CMAKE_CXX_STANDARD 14)

include_directories(headers)
include_directories(sources)

add_executable(FarmaManage
        headers/consultas.h
        headers/diagnostico.h
        headers/domicilio.h
        headers/fecha.h
        headers/hora.h
        headers/indextuple.h
        headers/medicamento.h
        headers/medicos.h
        headers/nombre.h
        headers/pacientes.h
        headers/pacientesFile.h
        sources/consultas-file.cpp
        sources/diagnosticos-file.cpp
        sources/medicamentos-file.cpp
        sources/medicos-file.h
        sources/pacientes-file.cpp
        testing.cpp)
