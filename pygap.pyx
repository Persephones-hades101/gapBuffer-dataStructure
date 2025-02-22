# distutils: language = c++

from libcpp.vector cimport vector
from libcpp.string cimport string

cdef extern from "gap_buffer_3.cpp":
    void   resizeBuffer                    (vector[char]& buffer, int& gap_start, int& gap_end)
    void   printBuffer                     (vector[char]& v)
    string printText                       (vector[char]& v)
    void   insert_in_buffer                (vector[char]& buffer, int& gap_start, int& gap_end, char x)
    void   move_cursor_left                (vector[char]& buffer, int& gap_start, int& gap_end)
    void   move_cursor_right               (vector[char]& buffer, int& gap_start, int& gap_end)
    void   delete_                         (vector[char]& buffer, int& gap_start)
    void   insert_in_buffer_multiple_times (vector[char]& buffer, int& gap_start, int& gap_end)

cdef class GapBuffer:
    cdef vector[char] buffer
    cdef int gap_start
    cdef int gap_end

    def __cinit__(self, initial_size=10):
        self.buffer.resize(initial_size, '_')
        self.gap_start = 0
        self.gap_end   = initial_size - 1

    def resize_buffer(self):
        resizeBuffer(self.buffer, self.gap_start, self.gap_end)

    def print_buffer(self):
        printBuffer(self.buffer)

    def print_text(self):
        return printText(self.buffer).decode('utf-8')

    def insert(self, str x):
        for i in x.encode('utf-8'): # Convert Python string to C++ char
            insert_in_buffer(self.buffer, self.gap_start, self.gap_end, i)

    def move_left(self):
        move_cursor_left(self.buffer, self.gap_start, self.gap_end)

    def move_right(self):
        move_cursor_right(self.buffer, self.gap_start, self.gap_end)

    def delete(self):
        delete_(self.buffer, self.gap_start)

    def insert_multiple_times(self):
        insert_in_buffer_multiple_times(self.buffer, self.gap_start, self.gap_end)

