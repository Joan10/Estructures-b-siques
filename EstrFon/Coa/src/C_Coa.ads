--
-- To change this template, choose Tools | Templates
-- and open the template in the editor.
--

--------------------------------------------------------------------------------
-- File: P_Pila.ads
--
-- Created on 17/02/2011
--------------------------------------------------------------------------------

--
-- Description of P_Pila
--
-- @author joan
-- 
package C_Coa is

    type Coa is limited private;

    procedure cBuida (c: out Coa);
    procedure Posa (c: in out Coa; x: in character);
    procedure EliminaPrimer (c: in out Coa);
    function SelPrimer(C: in Coa) return character;
    function esBuida(c: in Coa) return boolean;

    Mal_Us: Exception;
    Desbordament: Exception;

    Private
        MAX: Integer:=100;

        type index is new integer range 0 .. max;
       -- type Pila is access bloc;
        type Coa is
            record
	      p,q: index;
            end record;

end C_Coa;
