with Ada.IO_Exceptions;

package RegNrParser is
    function CharToInt (C: Character) return Integer;
    function ParsePlate (Plate: String) return Integer;
end RegNrParser;
