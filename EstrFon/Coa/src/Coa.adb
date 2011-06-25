-- 
-- To change this template, choose Tools | Templates
-- and open the template in the editor.
-- 

--------------------------------------------------------------------------------
-- File: Coa.adb
--
-- Created on 22/02/2011
--------------------------------------------------------------------------------
with Ada.Text_IO; use Ada.Text_IO;
with ada.integer_text_io; use ada.integer_text_io;
with C_Coa; Use C_Coa;
--
-- Description of Pila
--
-- @author joan
--
procedure Coa is
    o: character := ' ';
    C: C_Coa.Coa;



    procedure Menu is
    begin
    new_line;
    Ada.Text_IO.Put_Line ("PILA");
    Put_Line("a. Posa");
    Put_Line("b. Treu primer");
    Put_Line("c. Selecciona Primer");
    Put_Line("d. Buida?");
    Put_Line("e. Pila nova");
    end Menu;
begin

    C_Coa.cBuida(C);

    while o /= 's' loop
    if (o = 'a') then
        Ada.Text_IO.Put_Line ("Escriu caràcter:");
        Get_Immediate(o);
        C_Coa.Posa(C,o);
                Put(o);
                new_line;
    elsif o = 'b' then
        C_Coa.EliminaPrimer(C);
    elsif o = 'c' then
        Ada.Text_IO.Put(C_Coa.SelPrimer(C));
    elsif o = 'd' then
        if esBuida(C) then
            Put_Line("Buida");
        else
            Put_Line("No buida");
        end if;
    end if;
    Menu;
    get_immediate(o);
    new_line;
    end loop;
end Coa;