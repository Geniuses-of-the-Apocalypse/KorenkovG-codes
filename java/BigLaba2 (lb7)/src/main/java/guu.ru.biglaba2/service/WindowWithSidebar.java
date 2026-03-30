package guu.ru.biglaba2.service;

import org.springframework.beans.factory.config.ConfigurableListableBeanFactory;
import org.springframework.context.annotation.Scope;
import org.springframework.stereotype.Service;

@Service("sidebar")
@Scope(ConfigurableListableBeanFactory.SCOPE_PROTOTYPE)
public class WindowWithSidebar extends WindowDecorator {

    public WindowWithSidebar(IWindow decoratedWindow) {
        super(decoratedWindow);
    }

    @Override
    public String draw() {
        return super.draw() + " + Sidebar";
    }
}