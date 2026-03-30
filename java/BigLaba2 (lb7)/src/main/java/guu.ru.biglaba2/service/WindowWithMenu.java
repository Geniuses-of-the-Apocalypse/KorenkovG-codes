package guu.ru.biglaba2.service;

import org.springframework.beans.factory.config.ConfigurableListableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Service;

@Service("menu")
@Scope(ConfigurableListableBeanFactory.SCOPE_PROTOTYPE)
public class WindowWithMenu extends WindowDecorator {

    public WindowWithMenu(IWindow decoratedWindow) {
        super(decoratedWindow);
    }

    @Override
    public String draw() {
        return super.draw() + " + Menu";
    }
}