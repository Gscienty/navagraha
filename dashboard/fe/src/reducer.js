import thunkMiddleware from 'redux-thunk';
import namespace from './reducers/namespace';
import systemInfo from './reducers/system_info';
import repo from './reducers/repo';
import func from './reducers/func';
import code from './reducers/code';
import { combineReducers, createStore, applyMiddleware } from 'redux';

const rootReducer = combineReducers({
    namespace,
    systemInfo,
    repo,
    func,
    code
});

export default createStore(rootReducer, applyMiddleware(thunkMiddleware));
