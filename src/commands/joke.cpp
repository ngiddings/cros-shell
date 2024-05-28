/*
 * Created by connor on 2/7/24.
 * 16 of the classiest jokes.
 */

#include <stdio.h>
#include <stdlib.h>

void joke() {
    const char* jokes[] = {
        "What do you call a factory that makes okay products? \nA satisfactory.",
        "What did one wall say to the other? \nI'll meet you at the corner.",
        "What did the zero say to the eight? \nThat belt looks good on you.",
        "If my wife thinks I'm obsessed with programming, she's crazy. \nendif.",
        "Hey girl, are you an object-oriented programming language?\nBecause you've got class.",
        "How many lightbulbs does it take to change a programmer? \nI don't know, but it sounds like somebody learned about dependency inversion.",
        "[\"Hip\",\"Hip\"]\nHip Hip Array!",
        "Why do programmers prefer dark mode?\nBecause the light attracts bugs!",
        "Why don't scientists trust atoms?\nBecause they make up everything!",
        "Why do Java developers wear glasses?\nBecause they don't see sharp!",
        "Why did the programmer quit his job?\nHe didn't get arrays!",
        "Why did the scarecrow win an award?\nBecause he was outstanding in his field!",
        "I told my wife she was drawing her eyebrows too high.\nShe looked surprised!",
        "I asked the librarian if the library had any books on paranoia.\nShe whispered, 'They're right behind you.'",
        "I used to play piano by ear. \nNow I use my hands and fingers.",
        "I told my wife she should embrace her mistakes.\nShe gave me a hug."};

    int joke_index = rand() % 16;
    printf("%s\n", jokes[joke_index]);
}

int main() {
    joke();
    return 0;
}
