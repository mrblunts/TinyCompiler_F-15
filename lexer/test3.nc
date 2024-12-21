! Program 1: To read two values and print their absolute difference
PROGRAM absdiff
INTEGER a
INTEGER b
INTEGER c
READ *, a, b ! reads a and b in free format
IF (a .GT. b) THEN
c = a - b
ELSE
IF (a .LT. b) THEN
c = b - a
ELSE
c = 0
END IF
END IF
PRINT *, "Absolute Difference of", a, "and", b, "is", c
END PROGRAM absdiff