module EventExample; reg a, b; integer time_counter; always @(a or b) begin $display("@(a or b) event triggered at time %0t", $time); time_counter = time_counter + 1; end always @(a | b) begin $display("@(a | b) event triggered at time %0t", $time); time_counter = time_counter + 1; end initial begin a = 0; b = 0; time_counter = 0; // Simulate changing values of a and b 
repeat (10) begin #10; a = !a; #15; b = !b; end
 // Display the total number of triggered events 
 $display("Total triggered events: %d", time_counter); $finish; end endmodule