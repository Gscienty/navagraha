package nava.function;

import nava.model.IHandler;
import nava.model.IRequest;
import nava.model.IResponse;
import nava.model.Response;
import nava.function.Function;

public class Handler implements IHandler {
    public IResponse handle(IRequest request) {
        IResponse res = new Response();
        res.setBody(Function.exec(request.getBody()));
        return res;
    }
}
