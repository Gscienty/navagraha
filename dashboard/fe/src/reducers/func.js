import {
    FUNC_LIST_REQUEST_POST,
    FUNC_LIST_RECEIVE_POST,
    FUNC_UP_POST,
    FUNC_DOWN_POST,
    FUNC_LIST_SET,
    FUNC_LIST_UNSET,

    FUNC_DETAIL_SET,
    FUNC_DETAIL_UNSET,
    FUNC_DETAIL_FETCH_RECEIVE,
    FUNC_DETAIL_FETCH_REQUEST
} from '../actions/func';

const initState = {
    state: FUNC_LIST_UNSET,
    namespace: 'unset',
    func: [],

    funcDetail: null,
    funcDetailState: FUNC_DETAIL_UNSET
};

export default function funcReduce(state = initState, action) {

    switch (action.type) {

        case FUNC_LIST_REQUEST_POST:
            return state;

        case FUNC_LIST_RECEIVE_POST:
            return Object.assign({}, state, {
            type: FUNC_LIST_SET,
            namespace: action.namespace,
            func: action.func
        });

        case FUNC_UP_POST:
            return state;

        case FUNC_DOWN_POST:
            return state;

        case FUNC_DETAIL_FETCH_RECEIVE:
            return Object.assign({}, state, {
            funcDetail: action.detail,
            funcDetailState: FUNC_DETAIL_SET
        });

        case FUNC_DETAIL_FETCH_REQUEST:
            return Object.assign({}, state, {
            funcDetail: null,
            funcDetailState: FUNC_DETAIL_UNSET
        });

        default:
            return state;
    };
};

