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
package body C_Pila is

    type bloc is
        record
            x: character;
            s: index;
        end record;

    type memoria is array(index range 1..index'last) of bloc;

    m: memoria;
    lliure: index;

    procedure pBuida (p: out Pila) is
        q: Pila;
    begin
        q.p := index(0);
        p := q;
    end pBuida;
    
    procedure Empila (p: in out Pila; x: in character) is
	q: index;
    begin
	if lliure = 0 then raise Desbordament; end if;
	q := lliure;
	lliure := m(lliure).s;
	m(q).x := x;
	m(q).s := p.p; p.p := q;
      end Empila;


    procedure Desempila (p: in out Pila) is
        q: index;
    begin
        if p.p = index(0) then raise Mal_Us; end if;
        q := p.p;
        p.p := m(q).s;
        m(q).s := lliure; lliure := p.p;
    end Desempila;


    function Cim(p: in Pila) return character is
    begin
        if (p.p = index(0)) then raise Mal_Us; end if;
        return m(p.p).x;
    end Cim;

    function esBuida(p: in Pila) return boolean is
    begin
        return p.p = 0;
    end esBuida;

    begin

        lliure := 1;

        for i in 1..(MAX-1) loop
            m(index(i)).s := index(i+1);
        end loop;
        m(index(MAX)).s := 0;

    
end C_Pila;

