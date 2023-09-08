module mux21 (
    a,b,sel,y
);
    input a,b;
    input sel;
    output y;
    assign y=sel?b:a;
endmodule