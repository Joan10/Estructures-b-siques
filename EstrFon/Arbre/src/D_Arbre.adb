-- 
-- To change this template, choose Tools | Templates
-- and open the template in the editor.
-- 

--------------------------------------------------------------------------------
-- File: D_Arbre.adb
--
-- Created on 04/03/2011
--------------------------------------------------------------------------------

--
-- Description of D_Arbre
--
-- @author joan
--
with P_Pila;
with ada.text_io; use ada.text_io;
package body D_Arbre is

    procedure ABuit(a: out arbre) is
        arrel: pnode renames a.arrel;
    begin
        arrel:=null;
    end ABuit;

    procedure Empelta(a: out arbre; ae,ad: in arbre; x: in character) is
    begin
        a.arrel:=new node;
        a.arrel.all.x := x;
        a.arrel.all.Fesq := ae.arrel;
        a.arrel.all.Fdret := ad.arrel;
    end Empelta;

    function Fesq(a: in arbre) return arbre is
        B: Arbre;
    begin
        B.arrel := a.arrel.all.Fesq;
        return B;
    end Fesq;

    function  ExFesq(a: in arbre) return boolean is
        
    begin
         return a.arrel.all.Fesq /= null;
         exception
            when CONSTRAINT_ERROR => return false;
    end ExFesq;

    function Fdret(a: in arbre) return arbre is
         B: Arbre;
    begin
        B.arrel := a.arrel.all.Fdret;
        return B;
    end Fdret;

    function  ExFdret(a: in arbre) return boolean is
    begin
         return a.arrel.all.Fdret /= null;
         exception
            when CONSTRAINT_ERROR => return false;
    end ExFdret;

    function Contingut_Arrel(a: in arbre) return character is
    begin
        return a.arrel.all.x;
    end Contingut_Arrel;

    procedure RecorrInordre(a: in arbre) is
        package P_PilaA is new P_Pila(Arbre); Use P_PilaA;
        P: P_PilaA.Pila;
        A2: Arbre;
        begin
        A2:=A; while (ExFdret(A2) = true) loop P_PilaA.Empila(P,A2); A2:=fEsq(A2); end loop;
        P_PilaA.Empila(P,A2);

        while not( P_PilaA.esBuida(P)) loop
            A2 :=  P_PilaA.Cim(P);  P_PilaA.desempila(P);
            Put(A2.arrel.all.x);
            if ExFdret(A2) then 
                A2:=Fdret(A2);
                while ExFEsq(A2) loop
                    empila(p,A2); A2:=Fesq(A2);
                end loop;
                empila(p,A2);
            end if;
        end loop;


    end RecorrInordre;

    procedure RecorrPreOrdre(a: in arbre) is
        package P_PilaA is new P_Pila(Arbre); Use P_PilaA;
        P: P_PilaA.Pila;
        A2: Arbre;
      begin
        P_PilaA.pBuida(P);
        P_PilaA.Empila(P,A);

        while not(P_PilaA.esBuida(P)) loop
            A2:=P_PilaA.Cim(P); P_PilaA.Desempila(P);
            Put(A2.arrel.all.x);
            if ExFdret(A2) then Empila(P,Fdret(A2)); end if;
            if ExFesq(A2) then Empila(P,Fesq(A2)); end if;
        end loop;
    end RecorrPreOrdre;

    procedure RecorrPostOrdre(a: in arbre) is

        type S_Node is record
            n: arbre;
            is_atom: boolean;
        end record;
        
        package P_PilaA is new P_Pila(S_Node); Use P_PilaA;
        P: P_PilaA.Pila;
        R_Aux: S_Node;
        A_Aux: Arbre;
      begin
        P_PilaA.pBuida(P);

        R_Aux.n := A; R_Aux.is_atom := false;
        P_PilaA.Empila(P,R_Aux);

        while not(P_PilaA.esBuida(P)) loop
          R_Aux := cim(P); P_PilaA.Desempila(P);

            if (R_Aux.is_atom) then
                Put(R_Aux.n.arrel.all.x);
            else
                R_Aux.is_atom := true;
                P_PilaA.Empila(P,R_Aux);
                A_Aux := R_Aux.n;
                if ExFdret(A_Aux) then R_Aux.n := Fdret(A_Aux); R_Aux.is_atom := false; Empila(P,R_Aux); end if;
                if ExFesq(A_Aux) then R_Aux.n := Fesq(A_Aux); R_Aux.is_atom := false; Empila(P,R_Aux); end if;
            end if;
        end loop;
    end RecorrPostOrdre;
end D_Arbre;