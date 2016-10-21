package body RegNrParser is
    function CharToInt (C: Character) return Integer
    is
        N: Integer;
    begin
        N := Character'Pos(C);
        if N >= Character'Pos('A') and N <= Character'Pos('Z') then
            return N - Character'Pos('A');
        elsif N >= Character'Pos('0') and N <= Character'Pos('9') then
            return N - Character'Pos('0');
        else
            return 0;
        end if;
    end CharToInt;

    function ParsePlate (Plate: String) return Integer
    is
        N: Integer;
    begin
        N := 676000*CharToInt(Plate(Plate'First))
            + 26000*CharToInt(Plate(Plate'First+1))
            + 1000*CharToInt(Plate(Plate'First+2))
            + 100*CharToInt(Plate(Plate'First+3))
            + 10*CharToInt(Plate(Plate'First+4))
            + CharToInt(Plate(Plate'First+5));
        return N;
    end ParsePlate;
end RegNrParser;
