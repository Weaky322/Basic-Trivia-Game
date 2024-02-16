// A simple trivia game
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define POOL_SIZE 5 // this will be a larger value later

typedef struct
{
    char question[256];
    char options[4][256];
    int correct_option;
} Question;

void displayQuestion(Question q)
{
    printf("%s\n", q.question);
    for (int i = 0; i < 4; i++)
    {
        printf("%d. %s\n", i + 1, q.options[i]);
    }
}

int checkAnswer(Question q, int user_input)
{
    return (user_input == q.correct_option);
}

int main()
{
    srand(time(NULL));

    int valid;

    Question question_pool[POOL_SIZE] = // note to self: the # of questions cannot exceed the value of POOL_SIZE
    {
        { "When did 'Sonic the Hedgehog' release for the SEGA Genesis?",
            { "1989", "1990", "1994", "1991" }, 4
        },
        { "What is the acronym for the colors of the rainbow?",
            { "RGB", "RBGCMYK", "ROYGBIV", "CMYK" }, 3
        },
        { "What color is a giraffe's tounge?",
            { "Gray", "Black", "Blue", "Red" }, 2
        },
        { "Which of the following is the national beverage of 20 of the United States?",
            { "Coca-Cola", "Water", "Milk", "Root Beer" }, 3
        },
        { "Which of the United States came first?",
            { "Delaware", "Pennsylvania", "New Jersey", "Georgia" }, 1
        },
    };

    Question questions[POOL_SIZE];
    memcpy(questions, question_pool, sizeof(question_pool));

    printf("Trivia Game!\n");

    int num_questions = POOL_SIZE;
    int score = 0;

    for (int i = 0; i < POOL_SIZE; i++)
    {
        int random_index = rand() % num_questions;
        Question current_question = questions[random_index];
        displayQuestion(current_question);
 
        int user_answer;
        int rc;
        printf("Enter your answer (1-4): ");

        while ((rc = scanf("%d", &user_answer)) == 0 || user_answer < 1 || user_answer > 4)
        {
            scanf("%*[^\n]");
            printf("Enter your answer (1-4): ");
        }
        if (checkAnswer(current_question, user_answer))
        {        
            printf("Correct!\n\n");
            score++;
        }
        else
        {
            printf("Incorrect. The correct answer is %d. %s\n\n", current_question.correct_option,
                current_question.options[current_question.correct_option- 1]);
        }
        
        questions[random_index] = questions[num_questions - 1];
        num_questions--;
    }

    return 0;
}
