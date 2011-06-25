-- 
-- To change this template, choose Tools | Templates
-- and open the template in the editor.
-- 

--------------------------------------------------------------------------------
-- File: P_Pila.adb
--
-- Created on 17/02/2011
--------------------------------------------------------------------------------
--
-- Description of P_Pila
--
-- @author joan
--
package body P_Pila is

    procedure pBuida (p: out Pila) is
    begin
        p := null;
    end pBuida;
    
    procedure Empila (p: in out Pila; x: in Element) is
    begin
        p := new bloc'(x, p);
        exception
            when storage_error => raise Desbordament;
    end Empila;


    procedure Desempila (p: in out Pila) is
    begin
        p:=p.all.s;
    end Desempila;


    function Cim(p: in Pila) return Element is
    begin
        if (p = null) then raise Mal_Us; end if;
        return p.all.c;
    end Cim;

    function esBuida(p: in Pila) return boolean is
    begin
        return p = null;
    end;

end P_Pila;

