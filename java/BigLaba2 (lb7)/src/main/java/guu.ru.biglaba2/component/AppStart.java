package guu.ru.biglaba2.component;

import lombok.extern.log4j.Log4j2;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import guu.ru.biglaba2.service.WindowBean;

@Component
@Log4j2
public class AppStart {

    @Autowired
    private WindowBean windowBean;

    public void start() {
        log.info("Result: {}", windowBean.drawWindow());
    }
}