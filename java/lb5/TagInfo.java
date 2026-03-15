package GUU.RU.Laba5J;

/**
 * Класс для хранения информации о найденном HTML-теге
 */
public class TagInfo {
    private String tagName;
    private int lineNumber;
    private int position;
    private String context;

    public TagInfo(String tagName, int lineNumber, int position, String line) {
        this.tagName = tagName;
        this.lineNumber = lineNumber;
        this.position = position;

        int start = Math.max(0, position - 21);             // контекст для понимания, где находится тег
        int end = Math.min(line.length(), position + 20);
        this.context = line.substring(start, end).trim();
    }

    public String getTagName() { return tagName; }
    public int getLineNumber() { return lineNumber; }
    public int getPosition() { return position; }
    public String getContext() { return context; }

    @Override
    public String toString() {
        return String.format("Строка %d, позиция %d: <%s> | ...%s...",
                lineNumber, position, tagName, context);
    }
}

