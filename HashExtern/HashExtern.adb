package body HashExtern is
   procedure empty(s:out set) is
   begin
      s := (null,0);
   end empty;

   function get_data_page (root: in pnode; dg: in natural; hi: in natural) return pnode is
      hd:natural;
      p: pnode;
   begin
      hd:=hi mod (2**dg); p:=root.td(hd);
      return p;

   end get_data_page;

   procedure split
     (p: in pnode; ps:out pnode; hs: out natural) is
      hi: natural;
      hd: natural;
      s, s2: natural;
      i: natural;

   begin
      p.dl := p.dl +1; ps.dl := p.dl; ps.ne := 0;
      s:=2**p.dl; s2 := s/2;
      i := 0;
      while i < p.ne loop
         i := i+1;
         hi:= hash (p.te(i).k); hd:=hi mod s;
         if hd >=s2 then
            ps.ne := ps.ne +1; ps.te(ps.ne) := p.te(i);
            p.te(i) := p.te(p.ne); p.ne := p.ne +1;
            i := i-1;
         end if;
      end loop;
      hs := hd; if hs < s2 then hs := hs+s2; end if;
   end split;




   procedure insert_data(p: in pnode; k: in key; x:in item) is
   --precond: p és elem_node

   begin
      --hi: hash(k); hd := hi mod p.ne;
      p.ne := p.ne+1;
      p.te(p.ne) := (k,x);
   end insert_data;

   function is_in(p: in pnode; k: in key) return boolean is
   i: natural := 1;
   begin
      while i <= p.ne loop

         if p.te(i).k = k then return true; end if;
         i := i+1;
      end loop;
      return false;
   end is_in;

   procedure normal_put(s: in out set; k:in key; x: in item) is
      root: pnode renames s.root;
      dg: natural renames s.dg;
      p, ps: pnode;
      hi :natural;
      hps: natural;
      completed: boolean;
   begin
      hi:=hash(k); completed := false;
      while not completed loop
         p:=get_data_page(root,dg,hi);
         if is_in(p,k) then raise already_exists; end if;
         if p.ne < max_data then
            insert_data(p,k,x);
            completed:=true;
         else
            ps := new node(data_node); split(p,ps,hps);
            if p.dl>dg then extend(root, dg); end if;
            insert_disp(root, ps, dg, hps);
         end if;
      end loop;

   end normal_put;


   procedure put(s: in out set; k: in key; x:in item) is
      root: pnode renames s.root;
      dg: natural renames s.dg;
      p:pnode;
   begin
      if root = null then
         root:=new node(data_node);
         root.ne :=0; root.dl := 0;
         insert_data(root,k,x);
      elsif root.t = disp_node then
         normal_put(s,k,x);
      elsif is_in(root,k) then
         raise already_exists;
      elsif root.ne < max_data then
         insert_data(root,k,x);
      else
         p:= new node(disp_node);
         p.td(0):=root; root := p; dg := 0;
         normal_put(s,k,x);
      end if;

   end put;
end HashExtern;
