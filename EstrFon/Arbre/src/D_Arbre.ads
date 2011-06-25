--
-- To change this template, choose Tools | Templates
-- and open the template in the editor.
--

--------------------------------------------------------------------------------
-- File: D_Arbre.ads
--
-- Created on 04/03/2011
--------------------------------------------------------------------------------

--
-- Description of D_Arbre
--
-- @author joan
--
package D_Arbre is
    
    type Arbre is private ;
    procedure ABuit(a: out arbre);
    procedure Empelta(a: out arbre; ae,ad: in arbre; x: in character);
    function Fesq(a: in arbre) return arbre;
    function  ExFesq(a: in arbre) return boolean;
    function Fdret(a: in arbre) return arbre;
    function ExFdret(a: in arbre) return boolean;

    function Contingut_Arrel(a: in arbre) return character;

    procedure RecorrInordre(a: in arbre);
    procedure RecorrPreOrdre(a: in arbre);
    procedure RecorrPostOrdre(a: in arbre);

    private
        type node;
        type pnode is access node;
        type node is record 
            x:character;
            Fesq, Fdret: pnode;
        end record;

        type Arbre is record 
            arrel: pnode;
        end record;
    
end D_Arbre;
