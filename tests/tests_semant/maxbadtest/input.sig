PROGRAM MAXBADTEST;
CONST
    MAXBADTEST = 10;
    SOME = 20;
    SOME2 = 40;
	BEGIN
    MAXBADTEST := 30;
    VSOME := 10;
    VSOME2 := UNKNW + 40;
    CASE VSOME2 + UNKNW - 5 OF
    VSOME - 1:
        /UNKNW := 40 + 5 - VSOME;\
    VSOME + 5:
        /RESULT2 := 50 + VSOME + 5;\
    ENDCASE;
    RESULT3 := UNKNW + 5;
	END.