class GameSingleton
{
    private:
        static GameSingleton* instance;

        GameSingleton();

    public:
        static GameSingleton* GetInstance();
};