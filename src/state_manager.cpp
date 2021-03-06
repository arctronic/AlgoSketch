#include <state_manager.hpp>
#include <array_sketch.hpp>
#include <state.hpp>

StateManager::StateManager()
{
    this->currentState = nullptr;
}

StateManager::StateManager(WindowManager *applicationWindowManager, EventManager *applicationEventManager, ResourceManager *applicationResourceManager)
{
    setWindowManager(applicationWindowManager);
    setEventManager(applicationEventManager);
    setResourceManager(applicationResourceManager);
    this->perform(Action::ChangeToMainMenu);
}

StateManager::~StateManager()
{
    delete this->currentState;
}

void StateManager::setWindowManager(WindowManager *applicationWindowManager)
{
    this->windowManager = applicationWindowManager;
}

void StateManager::setEventManager(EventManager *applicationEventManager)
{
    this->eventManager = applicationEventManager;
}

void StateManager::setResourceManager(ResourceManager *applicationResourceManager)
{
    this->resourceManager = applicationResourceManager;
}

void StateManager::start()
{
    this->perform(Action::ChangeToMainMenu);
}

State *StateManager::getCurrentState()
{
    return this->currentState;
}

WindowManager *StateManager::getApplicationWindow()
{
    return this->windowManager;
}

EventManager *StateManager::getEventManager()
{
    return this->eventManager;
}

void StateManager::perform(Action action)
{
    switch (action)
    {
    case Action::ChangeToMainMenu:
    case Action::Back:
        changeState(new MainMenu(this));
        break;

    case Action::ChangeToNewSketchMenu:
        changeState(new NewSketchMenu(this));
        break;

    case Action::Array:
        changeState(new ArraySketchMenu(this));
        break;

    case Action::Run:
        getCurrentState()->getSketchContainer()->setPaused(false);
        break;

    case Action::Pause:
        getCurrentState()->getSketchContainer()->setPaused(true);
        break;

    case Action::Reset:
        getCurrentState()->getSketchContainer()->reset();
        break;

    case Action::QuitApplication:
        this->getApplicationWindow()->terminateWindow();

    default:
        break;
    }
}

void StateManager::changeState(State *newState)
{
    delete this->currentState;
    currentState = nullptr;
    this->currentState = newState;
}

void StateManager::update()
{
    if (this->currentState != nullptr)
        this->currentState->update();
}

void StateManager::render()
{
    if (this->currentState != nullptr)
        this->currentState->render();
}