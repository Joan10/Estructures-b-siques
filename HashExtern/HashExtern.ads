generic
   type key is private;
   type item is private;
   with function "=" (k1,k2: in key) return boolean;
   with function hash(k: in key) return natural;

package HashExtern is
   type set is limited private;

   space_overflow:exception;
   already_exists:exception;

   procedure empty(s:out set);
   procedure put(s: in out set; k: in key; x:in item);
   --function is_in (s: in set; x: in elem) return boolean;
   procedure remove (s: in out set; k: in key; x: in item);
   --function is_empty (s: in set) return boolean;

private
   type node;
   type pnode is access node;

   type nodetype is (disp_node,data_node);

   bdi_disp: constant natural :=10;
   max_disp: constant natural :=2**bdi_disp; --mida màxima taules dispersió.
   max_data: constant natural:=52; --mida màxima de les pàgines de data.

   type elem is record
      k:key;
      x:item;
   end record;

   type t_disp is array (natural range 0..max_disp-1) of pnode;
   type t_elements is array (natural range 1..max_data) of elem;

   type node (t: nodetype) is
      record
         case t is
            when disp_node =>
               td: t_disp;
            when data_node =>
               dl: natural;  -- profunditat local (bits de la tdisp emprats per ser seleccionada)
               ne: natural; -- nombre d'elements a cada pàgina.
               te: t_elements; --taula d'elements.
         end case;
      end record;

   type set is
      record
         root: pnode;
         dg:natural;
      end record;

end HashExtern;
