cmake_minimum_required(VERSION 3.20)

project(parkingSpaceReservationManagementSystem)

# æ≤Ã¨±‡“Î 
set(CMAKE_EXE_LINKER_FLAGS "-static") 

add_executable(
    parkingSpaceReservationManagementSystem 
    main.cpp 
    TimeTool.cpp Validator.cpp 
    Reservation.cpp ReservationList.cpp 
    ParkingSpace.cpp ParkingSpaceList.cpp 
    Bill.cpp BillList.cpp
    ParkingSystem.cpp BlackList.cpp
)