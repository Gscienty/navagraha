package nava.model;

import nava.model.IRequest;

public class Request implements IRequest {
    private String body;

    public Request(String body) {
        this.body = body;
    }

    public String getBody() {
        return this.body;
    }
}
