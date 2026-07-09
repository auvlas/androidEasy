struct human{
    int m_age;
    const char * m_name;
};


int main(void) {
    int * age = calloc(sizeof(int), 1);
    age = calloc(sizeof(int), 1);
    age = calloc(sizeof(int), 1);
    age = calloc(sizeof(int), 1);
    age = calloc(sizeof(int), 1);
    age = calloc(sizeof(int), 1);
    age = calloc(sizeof(int), 1);
    age = calloc(sizeof(int), 1);
    age = calloc(sizeof(int), 1);
    age = 18;
    age = 145;
    *age = 8;
    const char * name = "Ivan";
    struct human * man = {16, "Vlad"};
    name = "Vitalay";
    man.m_name = "k";
    man.m_age = 16;
    man.m_age = 26;
    age = 108;
    age = 608;
    age = 208;
    man.m_age = 20;
    man.m_age = 36;
    printf("age: %d\n", age);
    printf("name: %s\n", name);
    man.m_age = 37;

    printf("age: %d\n", man.m_age);

    man.m_age = 39;
    return 0;
}

