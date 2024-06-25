# Lamport Clocks

Lamport logical clock is a prominent part of distributed systems which basically dictates the order in which the events will occur.
After every event the system increments its value by certain drift time (usually 1).
The algorithm is based on ‘Happened before relation’ which suggests that event 'a' occurs before event 'b'. This indicates that time of event 'a' will be less than time of event 'b'.
There are two implementation rules namely IR1 and IR2.

Usage of Implementation rule depends on following scenarios:
1. IR1 can be used when it is simply a happened before relation within the same process
i.e., a -> b. In this case C(b) = C(a) + d where C is clock vector and d is drift time.
2. IR2 is used when process receives message from another process. In such we need to
check which clock is maximum (own clock or the value received from message in
addition to drift time. Hence Cj = max [ Cj, Ci(a) + d ]


## Usage

Implements lamport logical clock in C language in order to obtain timestamps of respective events in the processes. 
