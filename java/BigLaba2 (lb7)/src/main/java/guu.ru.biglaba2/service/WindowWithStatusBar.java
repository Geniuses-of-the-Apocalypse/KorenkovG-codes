package guu.ru.biglaba2.service;

import org.springframework.beans.factory.config.ConfigurableListableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Service;

@Service("status")
@Scope(ConfigurableListableBeanFactory.SCOPE_PROTOTYPE)
public class WindowWithStatusBar extends WindowDecorator {

    public WindowWithStatusBar(IWindow decoratedWindow) {
        super(decoratedWindow);
    }

    @Override
    public String draw() {
        return super.draw() + " + Status Bar";
    }
}