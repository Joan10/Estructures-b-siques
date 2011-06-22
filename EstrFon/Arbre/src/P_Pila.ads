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
Generic
type Element is private;

package P_Pila is

    type Pila is limited private;

    procedure pBuida (p: out Pila);
    procedure Empila (p: in out Pila; x: in Element);
    procedure Desempila (p: in out Pila);
    function Cim(p: in Pila) return Element;
    function esBuida(p: in Pila) return boolean;

    Mal_Us: Exception;
    Desbordament: Exception;

    Private
        MAX: Integer:=100;

        type bloc;
        type Pila is access bloc;
        type bloc is
            record
                c: Element;
                s: Pila; --Punter a bloc.
            end record;

end P_Pila;
