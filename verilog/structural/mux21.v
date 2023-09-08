module mux21 (
    a,b,sel,y
);
    input a,b;
    input sel;
    output y;
    wire w1,w2,w3;
    or a1(w2,a,w1);
    and a2(w3,b,sel);
    or o1(y,w2,w3);
    not n1(w1,sel);
endmodule