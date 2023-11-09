class vlsi;
    rand bit [3:0] a,b;

endclass

module top;
    vlsi c;

    initial begin
        c=new;
        c.randomize();
        $$display("a=%d  b=%d",c.a,c.b);
    end
endmodule