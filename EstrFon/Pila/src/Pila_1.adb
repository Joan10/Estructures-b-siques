-- 
-- To change this template, choose Tools | Templates
-- and open the template in the editor.
-- 

--------------------------------------------------------------------------------
-- File: Pila.adb
--
-- Created on 17/02/2011
--------------------------------------------------------------------------------

with Ada.Text_IO; use Ada.Text_IO;
with ada.integer_text_io; use ada.integer_text_io;
with P_Pila;

--
-- Description of Pila
--
-- @author joan
--
procedure Pila_1 is
    package P_PilaChar is new P_Pila(integer); Use P_PilaChar;
        
    o: character := ' ';
    n: integer;
    P1: P_PilaChar.Pila;
    P2 : P_PilaChar.Pila;
    procedure Empila(P: in out P_PilaChar.Pila) is

    begin
        Ada.Text_IO.Put_Line ("Escriu caràcter:");
        Get(n);
        P_PilaChar.Empila(P,n);
                Put(n);
                new_line;
    end Empila;

    procedure Desempila(P: in out P_PilaChar.Pila) is

    begin
        P_PilaChar.Desempila(P);
    end Desempila;

    procedure Menu is
    begin
    new_line;
    Ada.Text_IO.Put_Line ("PILA");
    Put_Line("a. Empila 1");
    Put_Line("b. Desempila 1");
    Put_Line("c. Cim Pila");
    Put_Line("d. Pila Buida?");
    Put_Line("e. Pila nova");
    Put_Line("i. Empila 2");
    Put_Line("j. Desempila 2");
    end Menu;
begin

    P_PilaChar.pBuida(P1);


    while o /= 's' loop
    if (o = 'a') then
        Empila(P1);
    elsif o = 'b' then
        Desempila(P1);
    elsif o = 'c' then
        Put(Cim(P1));
    elsif o = 'd' then
        if esBuida(P1) then
            Put_Line("Buida");
        else
            Put_Line("No buida");
        end if;
        
    elsif o = 'e' then
    
        P_PilaChar.pBuida(P1);
    elsif o = 'i' then
        Empila(P2);
    elsif o = 'j' then
        Desempila(P2);
    end if;
    Menu;
    get_immediate(o);
    new_line;
    end loop;
end Pila_1;