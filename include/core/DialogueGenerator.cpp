#include "DialogueGenerator.h"

DialogueGenerator::DialogueGenerator()
{
	greetings.values = { 	
		node_value("Hello. ", &before_names, 0.5),
		node_value("Hey! ", &before_names, 0.5),
		node_value("Good day! ", &before_names, 0.5),
		node_value("Howdy! ", &before_names, 0.5)
	};
	
	before_names.values = { 
		node_value("I'm ", &name, 1.0),
		node_value("My name is ", &name, 1.0),
		node_value("They call me ", &name, 1.0)
	};

	random_trivia.values = {
		node_value("If you look up to the sky, you may see clouds!"),
		node_value("Gosh darn it, those greenskins to the east are a real menace!"),
		node_value("The desert to the east is currently claimed by an army of greenskins!"),
		node_value("What do you want?"),
		node_value("You're one ugly fella!"),
		node_value("You're one good looking fella!"),
		node_value("Whats up?"),
		node_value("You seem poor, need some change?"),
		node_value("I wouldn't wanna mess with you!"),
		node_value("You looking for trouble?"),
		node_value("Think you're tough eh?"),
		node_value("Im kind of a big deal around these parts", &exclamation_mark, 0.3),
		node_value("I just love the color ", &colors, 1.0)
	};
	
	questions.values = {
		node_value("Do you want something?"),
		node_value("Im a great wizard", &exclamation_mark, 0.5),
		node_value("Are you here to exterminate the nasty greenskins to the east?", &exclamation_mark, 0.5),
		node_value("I'm a great magician", &exclamation_mark, 0.5),
		node_value("I'm think i'm the greatest, don't you agree?"),
		node_value("I'm famous!"),
		node_value("You probably know me", &exclamation_mark, 0.3),
		node_value("And you are?"),
		node_value("Pleased to meet you", &exclamation_mark, 0.5)
	};

	colors.values = {
		node_value("red", &exclamation_mark, 0.7), 
		node_value("green", &exclamation_mark, 0.7),
		node_value("blue", &exclamation_mark, 0.7),
		node_value("yellow", &exclamation_mark, 0.7),
		node_value("white", &exclamation_mark, 0.7),
		node_value("brown", &exclamation_mark, 0.7)
	};
	
	exclamation_mark.values = {
		node_value("!")
	};
	
	dot.values = {
		node_value(". ", &questions, 0.4)
	};
	
	annoyed.values = {
		node_value("You're annoying."),
		node_value("Go bother someone else."),
		node_value("Leave me alone!"),
		node_value("Buzz off! I'm busy!"),
		node_value("This is ridiculous, leave me alone!"),
	};
}

float DialogueGenerator::percent()
{
	return (static_cast<float>(generateRand() % 100)) / 100;
}

string DialogueGenerator::generate_dialogue(string my_name, array<bool, 4> personality, float annoyed_level, Character* player)
{
	name.values = { node_value(my_name, &dot, 1.0) };
	
	string text = "";
	node* current;
	
	//70% to greet if person is nice. otherwise 30%. If not greet, same check for question or random_trivia.
	current = percent() < (personality[NICE] ? 0.7 : 0.3) ? &greetings : 
		(percent() < (personality[NICE] ? 0.7 : 0.3) ? &questions : &random_trivia);
	
	//If person is annoyed, it overrides dialogue
	float true_annoyed_level = 1 - 1 / pow(1.1, annoyed_level * ( 1.0 - (personality[NICE] * 0.4 + personality[TALKATIVE] * 0.3) ));
	current = percent() < true_annoyed_level ? &annoyed : current;
	while(current != nullptr)
	{
		node_value n = current->values.at(generateRand() % current->values.size());
		text += n.value;
		if( !(percent() < (personality[TALKATIVE] ? 1.5 * n.probability : n.probability)) )
			break;
		current = n.next;
	}
	while(text.back() == ' ')
		text = text.substr(0,text.length()-1);
	//Add a dot if sentence not closed
	if( text.back() != '.' && text.back() != '!' && text.back() != '?' )
		text += ".";
		
	return text;
}