-- 
-- To change this template, choose Tools | Templates
-- and open the template in the editor.
-- 

--------------------------------------------------------------------------------
-- File: C_Coa.adb
--
-- Created on 22/02/2011
--------------------------------------------------------------------------------

--
-- Description of C_Coa
--
-- @author joan
--
with Ada.Text_IO; use Ada.Text_IO;
with ada.integer_text_io; use ada.integer_text_io;
package body C_Coa is

    type bloc is
    record
        x: character;
        s: index;
    end record;

    type memoria is array(index range 1..index'last) of bloc;

    m: memoria;
    lliure: index;

    procedure cBuida (c: out Coa) is
    begin
        put(Integer(C.p));
        if (integer(C.p) > 0) and integer(C.p) < MAX then
            m(C.p).s := lliure;
            lliure:=C.q;
        end if;
        C.p:=0; C.q:= 0;

    end cBuida;

    procedure Posa (c: in out Coa; x: in character) is
        r: index;
    begin
        if lliure = 0 then raise desbordament; end if;
        
        r:=lliure; lliure:=m(lliure).s;
        m(r).x := x; m(r).s := 0;
        
        if C.p = 0 then C.q := r; C.p:=r;
        else m(C.p).s := r; C.p:= r;
        end if;
    end Posa;

    procedure EliminaPrimer (c: in out Coa) is
        r: index;
    begin
        if C.q = 0 then raise Mal_Us ; end if;
	r := C.q; C.q:=m(C.q).s;
	if C.q = 0 then C.p:=0; end if;
        m(r).s := lliure; lliure := r;
    end EliminaPrimer;

    function SelPrimer(C: in Coa) return character is
        
    begin
        if C.q = 0 then raise mal_us; end if;
        return m(c.q).x;
    end SelPrimer;

    function esBuida(c: in Coa) return boolean is
        
    begin
        return C.q=0;
    end esBuida;

    
    begin

        lliure := 1;

        for i in 1..(MAX-1) loop
            m(index(i)).s := index(i+1);
        end loop;
        m(index(MAX)).s := 0;
end C_Coa;

