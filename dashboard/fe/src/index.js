import React from 'react';
import ReactDOM from 'react-dom';
import { Provider } from 'react-redux';
import { HashRouter, Route, Switch} from 'react-router-dom';
import { Layout } from 'antd';
import './index.css';
import * as serviceWorker from './serviceWorker';
import store from './reducer';
import 'antd/dist/antd.css';
import NavaMenu from './components/sidecar';
import NavaHeader from './components/nava_header';
import DashboardPage from './pages/dashboard';
import NamespacePage from './pages/namespace';
import FuncPage from './pages/func';
import MonitorPage from './pages/monitor';
import NodePage from './pages/node';
import ProjectPage from './pages/project';

const { Sider, Content, Footer, Header } = Layout;

ReactDOM.render((
    <Provider store={store}>
        <Layout>
            <Header>
                <NavaHeader />
            </Header>
            <Layout>
                <HashRouter>
                    <Sider>
                        <NavaMenu />
                    </Sider>
                    <Layout>
                        <Layout>
                            <Content style={{minHeight: 'calc(100vh - 130px)'}}>
                                    <Switch>
                                        <Route exact path="/" component={DashboardPage} />
                                        <Route exact path="/namespace" component={NamespacePage} />
                                        <Route exact path="/func" component={FuncPage} />
                                        <Route exact path="/monitor" component={MonitorPage} />
                                        <Route exact path="/node" component={NodePage} />
                                        <Route exact path="/project" component={ProjectPage} />
                                    </Switch>
                            </Content>
                        </Layout>
                        <Layout>
                            <Footer>Nava FaaS</Footer>
                        </Layout>
                    </Layout>
                </HashRouter>
            </Layout>
        </Layout>
    </Provider>
), document.getElementById('root'));

serviceWorker.unregister();
