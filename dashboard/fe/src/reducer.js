import thunkMiddleware from 'redux-thunk';
import namespace from './reducers/namespace';
import systemInfo from './reducers/system_info';
import { combineReducers, createStore, applyMiddleware } from 'redux';

const rootReducer = combineReducers({
    namespace,
    systemInfo
});

export default createStore(rootReducer, applyMiddleware(thunkMiddleware));
