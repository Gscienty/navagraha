package nava.model;

public class Response implements IResponse {

    private String body;

    public Response() {

    }

    public void setBody(String body) {
        this.body = body;
    }

    public String getBody() {
        return this.body;
    }
}
