-- 
-- To change this template, choose Tools | Templates
-- and open the template in the editor.
-- 

--------------------------------------------------------------------------------
-- File: Arbre.adb
--
-- Created on 04/03/2011
--------------------------------------------------------------------------------

with Ada.Text_IO; use Ada.Text_IO;
with ada.integer_text_io; use ada.integer_text_io;
with D_Arbre; use D_Arbre;
--
-- Description of Arbre
--
-- @author joan
--
procedure Arbre is
A1, A2, A3, A4, A5, A6, A7: D_Arbre.Arbre;


begin
    
    Empelta(A1,A2,A3,'a');
    Empelta(A4,A5,A6,'b');
    Empelta(A7,A1,A4, 'x');

    Ada.Text_IO.Put (Contingut_Arrel(FDret(A7)));
    new_line;
    Ada.Text_IO.Put ( Contingut_Arrel(Fesq(A7)));
    new_line;
    Ada.Text_IO.Put (Contingut_Arrel(A1));
    Ada.Text_IO.Put (Contingut_Arrel(A4));
    Ada.Text_IO.Put (Contingut_Arrel(A7));
    new_line;
    if (ExFesq(A1)) then Ada.Text_IO.Put_Line ("A1 té Fesq"); else Ada.Text_IO.Put_Line ("A1 no té Fesq"); end if;
    if (ExFdret(A1)) then Ada.Text_IO.Put_Line("A1 té Fdret"); else Ada.Text_IO.Put_Line ("A1 no té Fdret"); end if;
    if (ExFesq(A4)) then Ada.Text_IO.Put_Line("A4 té Fesq"); else Ada.Text_IO.Put_Line  ("A4 no té Fesq"); end if;
    if (ExFdret(A4)) then Ada.Text_IO.Put_Line ("A4 té Fdret"); else Ada.Text_IO.Put_Line ("A4 no té Fdret"); end if;
    if (ExFesq(A7)) then Ada.Text_IO.Put_Line ("A7 té Fesq"); else Ada.Text_IO.Put_Line ("A7 no té Fesq"); end if;
    if (ExFdret(A7)) then Ada.Text_IO.Put_Line ("A7 té Fdret"); else Ada.Text_IO.Put_Line ("A7 no té Fdret"); end if;

    D_Arbre.RecorrPreordre(A7);new_line;
    D_Arbre.RecorrPostordre(A7);new_line;
    D_Arbre.RecorrInordre(A7);
end Arbre;