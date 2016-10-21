with Ada.Text_IO;
use Ada.Text_IO;
with Ada.Command_Line;
with RegNrParser;

procedure Regnr is
    type PlateArray is array (1 .. 17576000) of Boolean;
    type Plate_Acc is access PlateArray;

    File : File_Type;
    Line : Integer;
    Plates : Plate_Acc;
begin
    Plates := new PlateArray;
    
    if Ada.Command_Line.Argument_Count = 0 then
        Put_Line ("Usage: regnr <file>");
        return;
    end if;

    Open(File => File,
         Mode => In_File,
         Name => Ada.Command_Line.Argument (1));

    Plates.all := (others => False);

    loop
        exit when End_of_File (File);
        Line := RegNrParser.ParsePlate (Get_Line(File));
        if Plates (Line) = True then
            Put_Line("Dubbletter");
            goto ExitProgram;
        end if;
        Plates.all (Line) := True;
    end loop;
    Put_Line("Ej dubblett");

    <<ExitProgram>>
    Close(File);
end Regnr;

