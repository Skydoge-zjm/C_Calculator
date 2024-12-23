cmake_minimum_required(VERSION 3.27)
project(Calculator C)

set(CMAKE_C_STANDARD 11)

add_executable(Calculator main.c
        Modules/DataType/DataType.h
        Error/Error.h
        Error/ErrorCollection.c
        IO/IO.h
        IO/user_instruction.c
        IO/input_basic.c
        IO/input_validity_check.c
        IO/input_validity_check.c
        calculate/calculate.h
        calculate/calculate.c
        calculate/operator.c
        Modules/SeqStack/SeqStack.h
        Modules/SeqStack/SeqStack.c
        Modules/DataType/DataType.c
        Modules/SeqList/SeqList.h
        Modules/SeqList/SeqList.c
        calculate/operator.h
        IO/input_fromfile.c
        Test/engine.c
        Test/engine.h
)
