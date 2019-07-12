package nava.model;

import nava.model.IRequest;
import nava.model.IResponse;

public interface IHandler {
    IResponse handle(IRequest request);
}
