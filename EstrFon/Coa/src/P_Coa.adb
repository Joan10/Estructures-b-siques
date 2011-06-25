-- 
-- To change this template, choose Tools | Templates
-- and open the template in the editor.
-- 

--------------------------------------------------------------------------------
-- File: P_Coa.adb
--
-- Created on 22/02/2011
--------------------------------------------------------------------------------

--
-- Description of P_Coa
--
-- @author joan
--
package body P_Coa is

    procedure cBuida (c: out Coa) is
    begin
        C.p:=null; C.q:= null;

        --p:=1; q:=1; n:= 0;
    end cBuida;

    procedure Posa (c: in out Coa; x: in character) is
        r: pNode;
    begin
--        if n=max then raise Desbordament; end if;
--       a(p) := x;
--        p := (p mod max)+1;
--        n := n+1;
        if C.p = null then
            C.p := new node;
            C.p.all.x := x;
            C.p.all.s := null;
            C.q := C.p;
        else
            r := new node;
            r.all.x := x;
            r.all.s := null;
            C.p.all.s := r;
            C.p := r;
        end if;
    end Posa;

    procedure EliminaPrimer (c: in out Coa) is

    begin
        if C.q = null then raise Mal_Us ; end if;
	C.q:=C.q.all.s;
	if C.q = null then C.p:=null; end if;
    end EliminaPrimer;

    function SelPrimer(C: in Coa) return character is
        
    begin
        if C.q = null then raise mal_us; end if;
        return C.q.all.x;
    end SelPrimer;

    function esBuida(c: in Coa) return boolean is
        
    begin
        return C.q=null;
    end esBuida;

end P_Coa;

