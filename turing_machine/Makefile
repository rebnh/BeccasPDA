TM: commands.o configuration_settings.o final_states.o input_alphabet.o input_strings.o main.o states.o tape_alphabet.o tape.o transition_function.o transition.o turing_machine.o uppercase.o
	g++ -o $@ $^

commands.o: commands.cpp commands.h turing_machine.h input_strings.h configuration_settings.h
	g++ -c $<

configuration_settings.o: configuration_settings.cpp configuration_settings.h
	g++ -c $<

final_states.o: final_states.cpp final_states.h
	g++ -c $<

input_alphabet.o: input_alphabet.cpp input_alphabet.h
	g++ -c $<

input_strings.o: input_strings.cpp input_strings.h
	g++ -c $<

main.o: main.cpp
	g++ -c $<

states.o: states.cpp states.h
	g++ -c $<

tape_alphabet.o: tape_alphabet.cpp tape_alphabet.h
	g++ -c $<

tape.o: tape.cpp tape.h
	g++ -c $<

transition_function.o: transition_function.cpp transition_function.h
	g++ -c $<

transition.o: transition.cpp transition.h
	g++ -c $<

turing_machine.o: turing_machine.cpp turing_machine.h
	g++ -c $<

uppercase.o: uppercase.cpp uppercase.h
	g++ -c $<

clean:
	rm -f *.o

immaculate: clean
	rm -f TM