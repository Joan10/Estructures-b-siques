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
package C_Pila is

    type Pila is limited private;

    procedure pBuida (p: out Pila);
    procedure Empila (p: in out Pila; x: in character);
    procedure Desempila (p: in out Pila);
    function Cim(p: in Pila) return character;
    function esBuida(p: in Pila) return boolean;

    Mal_Us: Exception;
    Desbordament: Exception;

    Private
        MAX: Integer:=100;

        type index is new integer range 0 .. max;
       -- type Pila is access bloc;
        type Pila is
            record
	      p: index;
            end record;

end C_Pila;
