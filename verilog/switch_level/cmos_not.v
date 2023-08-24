module cmos_not(output out,input in);
supply1 vdd;
supply0 gnd;

pmos (out,vcc,in);
nmos (out,gnd,in);
    
endmodule