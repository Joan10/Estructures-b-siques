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
package P_Coa is

    type Coa is limited private;

    procedure cBuida (c: out Coa);
    procedure Posa (c: in out Coa; x: in character);
    procedure EliminaPrimer (c: in out Coa);
    function SelPrimer(C: in Coa) return character;
    function esBuida(c: in Coa) return boolean;

    Mal_Us: Exception;
    Desbordament: Exception;

    Private
        type Node;
        type pNode is access Node;
        type Node is
            record
                x: character;
                s: pNode;
            end record;

        type Coa is record p,q: pNode; end record;

end P_Coa;
