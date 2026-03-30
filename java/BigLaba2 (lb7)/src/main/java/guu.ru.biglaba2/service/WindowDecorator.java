package guu.ru.biglaba2.service;

public abstract class WindowDecorator implements IWindow {
    protected final IWindow decoratedWindow;

    public WindowDecorator(IWindow decoratedWindow) {
        this.decoratedWindow = decoratedWindow;
    }

    @Override
    public String draw() {
        return decoratedWindow.draw();
    }
}