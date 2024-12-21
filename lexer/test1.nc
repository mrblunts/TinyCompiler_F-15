! Program 2: To read a natural number n and
! print the sum of natural numbers from 1 to n
PROGRAM sum
INTEGER n
INTEGER i
INTEGER s
READ *, n
s = 0
DO i = 1, n
s = s + i
END DO
PRINT *, "Sum of first n natural numbers is", s
END PROGRAM sum 